bool Collided(vec2 vert, vec2 vertOne, vec2 vertTwo, vec2 vertThree, vec2 vertFour)
{
    float DOne = (vertTwo.x - vertOne.x) * (vert.y - vertOne.y) - (vert.x - vertOne.x) * (vertTwo.y - vertOne.y);
    float DTwo = (vertThree.x - vertTwo.x) * (vert.y - vertTwo.y) - (vert.x - vertTwo.x) * (vertThree.y - vertTwo.y);
    float DThree = (vertFour.x - vertThree.x) * (vert.y - vertThree.y) - (vert.x - vertThree.x) * (vertFour.y - vertThree.y);
    float DFour = (vertOne.x - vertFour.x) * (vert.y - vertFour.y) - (vert.x - vertFour.x) * (vertOne.y - vertFour.y);
    if (DOne >= 0 && DTwo >= 0 && DThree >= 0 && DFour >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}