create_figure(
        "robot", --name
        0.0, 1.5, -2.0, -- position (x,y,z)
        1.0, 1.0, 1.0, -- scale (x,y,z)
        45.0, -- angle
        "cube", -- type
        { "resources/textures/cupcake.jpg" } -- textures
)
create_figure(
        "cube 1",
        1.0, 1.0, 1.0, -- position (x,y,z)
        1.0, 4.0, 1.0, -- scale (x,y,z)
        20, -- angle
        "cube", -- type
        { "resources/textures/cupcake.jpg" } -- textures
)
create_light(
        "light 1", --name
        0.0, 1.0, 1.0, -- position (x,y,z)
        0.8, 1.0, 1.0, -- scale (x,y,z)
        10,  -- angle
        "point" -- type
)

delete_all();