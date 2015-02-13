# Metal Box varible
i = 0
metalPosY = 525
metalPosX = 0
while i < 20:
    box = Crate(metalPosX, metalPosY, metalCrate)
    metalPosX += 50
    if(metalPosX == 200 or metalPosX == 400 or metalPosX == 800):
        metalPosX += 50
    elif(metalPosX == 600):
        metalPosX += 100
    else:
        all_boxes.add(box)
        sprite_list.add(box)
    i += 1

# Wooden Box
woodenPosX = 650
woodenPosY = 375
woodenBox = Crate(woodenPosX, woodenPosY, woodenCrate) 
box_list.add(woodenBox) 
all_boxes.add(woodenBox) 