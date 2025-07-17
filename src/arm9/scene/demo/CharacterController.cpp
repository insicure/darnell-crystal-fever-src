// CharacterController.cpp
#include "CharacterController.h"
#include "ppx/Math.hpp"
#include "ppx/Tracelog.hpp"
#include <cmath>

namespace ppx {

  void CharacterController::Update(bool isHeld_LEFT, bool isHeld_RIGHT, bool isDown_UP, bool isUp_UP, f32 dt) {
    // Handle horizontal movement input
    direction.x = 0;
    if (isHeld_LEFT) direction.x = -1.0f;
    if (isHeld_RIGHT) direction.x = 1.0f;
    if (isHeld_LEFT && isHeld_RIGHT) direction.x = 0;
    pressingKey = (direction.x != 0);

    // Handle jump input
    if (isDown_UP)
    {
      desiredJump = true;
      pressingJump = true;
    }
    if (isUp_UP) pressingJump = false;

    // Calculate desired velocity
    desiredVelocity = {direction.x*MAXSPEED, 0.0f};

    // apply gravity
    f32 newGravity = (2.0f * JUMP_HEIGHT) / (JUMP_APEX_TIME*JUMP_APEX_TIME);
    velocity.y += newGravity*gravMultiplier*dt;

    if (velocity.y >= GRAVITY_MAX_DOWN) velocity.y = GRAVITY_MAX_DOWN; 
    
    onGround = CheckGround();

    if (onGround)
    {
      jumpExtraCounter = 0;
      velocity.y = 0;
    }

    canJumpAgain = (jumpExtraCounter < JUMP_EXTRA);

    if (desiredJump && (jumpBufferCounter += dt) > JUMP_BUFFER) {
      TraceLog("%f", jumpBufferCounter.toFloat());
      desiredJump = false;
      jumpBufferCounter = 0;
    }

    if (!currentlyJumping && !onGround)
      coyoteTimeCounter += dt;
    else
      coyoteTimeCounter = 0;

    // Apply physics
    ApplyMovement(dt);

    if (desiredJump) 
    {
      DoJump();
      goto skip_calc_grav;
    }

    calculateGravity(dt);
    
skip_calc_grav:

    UpdatePosition(dt);
  }

  // Get the tile at map (x, y) in tiles, not pixels
  uint8_t get_tile(uint8_t* map_data, int map_width, int x, int y) {
      if (x < 0 || y < 0 || x >= map_width) return 1; // out of bounds = solid
      return map_data[y * map_width + x];
  }

  void CharacterController::UpdatePosition(f32 dt) {
    if (velocity.x != 0) {
      f32 newX = position.x + velocity.x*dt;
      f32 hbLeft = newX + hitbox.x;
      f32 hbRight = hbLeft + hitbox.width;

      int topTile = ((position.y + hitbox.y) / map_tile_size.y).toInt();
      int bottomTile = ((position.y + hitbox.y + hitbox.height - 1) / map_tile_size.y).toInt();

      if (velocity.x > 0) { // moving right
        int rightTile = (hbRight / map_tile_size.x).toInt();
        for (int ty=topTile; ty<=bottomTile; ty++) {
          if (get_tile(map_data, map_size.x.toInt(), rightTile, ty) == 1) {
            // Snap to left of the tile
            velocity.x = 0;
            position.x = rightTile * map_tile_size.x - hitbox.x - hitbox.width;
            goto skip_x;
          }
        }
      } else if (velocity.x < 0) { // moving left
        int leftTile = (hbLeft / map_tile_size.x).toInt();
        for (int ty=topTile; ty<=bottomTile; ty++) {
          if (get_tile(map_data, map_size.x.toInt(), leftTile, ty) == 1) {
            velocity.x = 0;
            position.x = (leftTile + 1) * map_tile_size.x - hitbox.x;
            goto skip_x;
          }
        }
      }

      position.x += velocity.x*dt;
    }

skip_x:
    if (velocity.y != 0) {
      f32 newY = position.y + velocity.y*dt;
      f32 hbTop = newY + hitbox.y;
      f32 hbBottom = hbTop + hitbox.height;

      int leftTile = ((position.x + hitbox.x) / map_tile_size.x).toInt();
      int rightTile = ((position.x + hitbox.x + hitbox.width - 1) / map_tile_size.x).toInt();

      if (velocity.y < 0) { // moving up
        int topTile = (hbTop / map_tile_size.y).toInt();
        for (int tx = leftTile; tx <= rightTile; ++tx) {
          if (get_tile(map_data, map_size.x.toInt(), tx, topTile) == 1) {
            velocity.y = 0;
            position.y = (topTile + 1) * map_tile_size.y - hitbox.y;
            return;
          }
        }
      }

      if (velocity.y > 0) { // moving down
        int bottomTile = (hbBottom / map_tile_size.y).toInt();
        for (int tx = leftTile; tx <= rightTile; ++tx) {
          if (get_tile(map_data, map_size.x.toInt(), tx, bottomTile) == 1) {
            velocity.y = 0;
            position.y = bottomTile * map_tile_size.y - hitbox.y - hitbox.height;
            return;
          }
        }
      }

      position.y += velocity.y*dt;
    }
  }

  void CharacterController::ApplyMovement(f32 dt) {
    if (enableAcceleration)
      runWithAcceleration(dt);
    else
    {
      if (onGround)
        runWithoutAcceleration(dt);
      else
        runWithAcceleration(dt);
    }
  }

  f32 MoveTowards(f32 current, f32 target, f32 maxDelta) {
      const f32 diff = target - current;
      
      // Handle non-negative maxDelta cases
      if (maxDelta >= 0.0f && Math::abs(diff) <= maxDelta) {
        return target;
      }
      
      // Handle movement direction
      if (diff > 0.0f) {
        return current + maxDelta;
      } 
      else if (diff < 0.0f) {
        return current - maxDelta;
      }
      // diff == 0 (no movement)
      return current;
  }

  void CharacterController::runWithAcceleration(f32 dt)
  {
    f32 acceleration = onGround ? GROUND_ACCELERATION : AIR_ACCELERATION;
    f32 deceleration = onGround ? GROUND_DECELERATION : AIR_DECELERATION;
    f32 turnSpeed = onGround ? GROUND_TURNSPEED : AIR_TURNSPEED;
    f32 maxSpeedChange = 0.0f;

    if (pressingKey) {
      if (std::signbit(direction.x.value) != std::signbit(velocity.x.value)) {
        maxSpeedChange = turnSpeed * dt;
      } else {
        maxSpeedChange = acceleration * dt;
      }
    } else {
      maxSpeedChange = deceleration * dt;
    }

    velocity.x = MoveTowards(velocity.x, desiredVelocity.x, maxSpeedChange);
  }

  void CharacterController::runWithoutAcceleration(f32 dt)
  {
    velocity.x = desiredVelocity.x;
  }

  bool CharacterController::CheckGround() {
    if (velocity.y <= 0) return false;

    f32 newY = position.y + 1;
    f32 hbTop = newY + hitbox.y;
    f32 hbBottom = hbTop + hitbox.height;

    int leftTile = ((position.x + hitbox.x) / map_tile_size.x).toInt();
    int rightTile = ((position.x + hitbox.x + hitbox.width - 1) / map_tile_size.x).toInt();

    if (velocity.y > 0) { // moving down
      int bottomTile = (hbBottom / map_tile_size.y).toInt();
      for (int tx = leftTile; tx <= rightTile; ++tx) {
        if (get_tile(map_data, map_size.x.toInt(), tx, bottomTile) == 1) {
          return true;
        }
      }
    }

    return false;
  }

  void CharacterController::calculateGravity(f32 dt)
  {
    // up
    if (velocity.y < -0.01f)
    {
      if (onGround) gravMultiplier = GRAVITY_DEFAULT_MULTIPLER;
      else
      {
        if (enableVaribleJump)
        {
          if (pressingJump && currentlyJumping)
            gravMultiplier = GRAVITY_UP_MULTIPLER;
          else
            gravMultiplier = JUMP_CUTOFF;
        }
        else gravMultiplier = GRAVITY_UP_MULTIPLER;
      }
    }

    // down
    else if (velocity.y > 0.01f)
    {
      if (onGround) gravMultiplier = GRAVITY_DEFAULT_MULTIPLER;
      else gravMultiplier = GRAVITY_DOWN_MULTIPLER;
    }

    // not moving
    else
    {
      if (onGround) currentlyJumping = false;
      gravMultiplier = GRAVITY_DEFAULT_MULTIPLER;
    }
  }

  void CharacterController::DoJump()
  {
    bool coyote = (coyoteTimeCounter > 0.03f && coyoteTimeCounter < JUMP_COYOTE);

    if (onGround || canJumpAgain || coyote)
    {
      desiredJump = false;
      jumpBufferCounter = 0;
      coyoteTimeCounter = 0;
      
      if (!onGround && !coyote) jumpExtraCounter++;
      
      f32 jumpSpeed = 2.0f * JUMP_HEIGHT / JUMP_APEX_TIME;
      if (velocity.y < 0)
        jumpSpeed = jumpSpeed - velocity.y;
      // else if (velocity.y > 0)
      //   jumpSpeed = jumpSpeed - velocity.y;

      velocity.y = -jumpSpeed;
      currentlyJumping = true;
    }

    if (JUMP_BUFFER == 0)
      desiredJump = false;
  }

}