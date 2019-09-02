/*A class for the movement of the blackhole*/
using UnityEngine;

public class BlackholeMovement : MonoBehaviour
{
    private float timer;//timer used for stopping the blackhole with the slow powerup

    public float timerInc = 10f;
    public float speedInc = 0.01f;
    public float speed = 0.03f;

    public void pausePowerup()
    {
        timer += timerInc;//increment timer
    }

    void FixedUpdate()
    {
        if (timer <= 0)//if timer runs out
        {
            speed += speedInc;//increase speed
            transform.Translate(speed, 0, 0);//add speed
        }
        else
        {
            timer -= Time.deltaTime;//decrement timer
        }
    }
}
