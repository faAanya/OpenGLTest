figure(
        'robot',
        0.0, 1.5, -2.0,
        1.0, 1.0, 1.0,
        45.0,
        'cube',
        { 'resources/textures/cupcake.jpg' }
)
figure(
        'cube 1',
        0.0, 0.0, 0.0,
        1.0, 1.0, 1.0,
        20,
        'cube',
        {'resources/textures/container2.png' }
)
light(
        'light 1',
        0.0, 1.0, 1.0,
        0.8, 1.0, 1.0,
        10,
        'spot'
)
pick_object('cube 1')
change_color(0.0,1.0,0.0)


delete_all();