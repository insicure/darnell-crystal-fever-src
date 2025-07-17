// CharacterController.h
#pragma once

#include "ppx/Rect.hpp"
#include "ppx/Vec2.hpp"
#include "ppx/f32.hpp"
#include <cstdint>

namespace ppx {

  struct CharacterController {
    // Configuration
    const f32 MAXSPEED = 140.0f;
    const f32 GROUND_ACCELERATION = 1300.0f;
    const f32 GROUND_DECELERATION = 2600.0f;
    const f32 GROUND_TURNSPEED = 1600.0f;

    const f32 AIR_ACCELERATION = 500.0f;
    const f32 AIR_DECELERATION = 300.0f;
    const f32 AIR_TURNSPEED = 1200.0f;

    const f32 GRAVITY_BASE = 10.0f;
    const f32 GRAVITY_DEFAULT_MULTIPLER = 1.0f;
    const f32 GRAVITY_UP_MULTIPLER = 1.0f;
    const f32 GRAVITY_DOWN_MULTIPLER = 3.2f;
    const f32 GRAVITY_MAX_DOWN = 600.0f;
    const f32 JUMP_HEIGHT = 59.0f;
    const f32 JUMP_APEX_TIME = 0.57f;
    const f32 JUMP_CUTOFF = 6.5f;
    const int JUMP_EXTRA = 0;
    const f32 JUMP_BUFFER = 0.15f;
    const f32 JUMP_COYOTE = 0.1f;

    bool enableAcceleration = true;
    bool enableVaribleJump = true;
    
    // State
    Vec2 position;
    Rect hitbox;
    Vec2 velocity;
    Vec2 direction;
    Vec2 desiredVelocity;
    bool onGround = false;
    bool pressingKey = false;
    bool pressingJump = false;
    bool desiredJump = false;
    bool currentlyJumping = false;
    bool canJumpAgain = false;
    
    // Counters
    f32 gravMultiplier = 1.0f;
    f32 jumpBufferCounter = 0.0f;
    int jumpExtraCounter = 0;
    f32 coyoteTimeCounter = 0.0f;

    // map
    uint8_t *map_data = nullptr;
    Vec2 map_size;
    Vec2 map_tile_size;

    CharacterController() {
      CalculateJumpPhysics();
    }

    void Update(bool isHeld_LEFT, bool isHeld_RIGHT, bool isDown_UP, bool isUp_UP, f32 dt);
    void ApplyMovement(f32 dt);
    void calculateGravity(f32 dt);
    bool CheckCollision(const Rect &rect);
    void UpdatePosition(f32 dt);
    void DoJump();
    bool CheckGround();
    bool isWalkable(int tileX, int tileY);

    void runWithAcceleration(f32 dt);
    void runWithoutAcceleration(f32 dt);

  private:
    f32 GRAVITY_VALUE = 0.0f;
    f32 JUMP_SPEED_VALUE = 0.0f;
        
    uint8_t GetTileIndex(f32 x, f32 y) const;
    int WorldPositionToTileCoordinate(f32 worldPos) const;
    void CalculateJumpPhysics()
    {
      GRAVITY_VALUE = (2.0f * JUMP_HEIGHT) / (JUMP_APEX_TIME * JUMP_APEX_TIME);
      JUMP_SPEED_VALUE = 2.0f * JUMP_HEIGHT / JUMP_APEX_TIME;
    }
  };

}