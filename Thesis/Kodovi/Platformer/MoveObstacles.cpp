for (auto &obs : m_Obstacles)
{
    obs.rotation += obs.speed * 90.0f * dt.GetMiliseconds();
    obs.position += obs.toChange * obs.speed * dt.GetMiliseconds();
    if (obs.orientation)
    {
        obs.travel = distance(obs.position, obs.startPosition);
    }
    else
    {
        obs.travel = distance(obs.position, obs.destination);
    }

    if (obs.toTravel < obs.travel)
    {
        obs.speed *= -1;
        obs.orientation = !obs.orientation;
    }
}