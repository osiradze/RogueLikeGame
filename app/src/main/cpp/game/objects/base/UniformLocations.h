//
// Shared OpenGL uniform location structs.
// Call glGetUniformLocation once during init and store results here.
//
#pragma once

// Uniforms used by the enemy compute shader
struct Uniforms {
    int u_model  = -1;
    int u_camera     = -1;
    int u_point_size = -1;
    int u_player_position   = -1;
    int u_delta_time        = -1;
    int u_enemy_count       = -1;
    int u_collision_radius  = -1;
    int u_detection_radius = -1;
    int u_floats_per_vertex = -1;
    int u_bounds            = -1;
    int u_ssbo_offset       = -1;
    int u_enemy_speed = -1;
    int u_bullet_radius = -1;
    int u_bullet_count = -1;
    int u_bullet_floats_per_vertex = -1;
    int u_impact_radius = -1;
};
