void explosionUpdate()
{

    objects[currentObject].counter++;
    if (objects[currentObject].counter % 2 != 0)
    {
        return;
    }

    if (objects[currentObject].state == 0)
    {
        objects[currentObject].active = 0;
        printBG();

        return;
    }

    animator();
}
