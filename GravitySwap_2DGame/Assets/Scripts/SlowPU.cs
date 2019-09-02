/*a powerup to stop blackhole movement for a short time*/
using UnityEngine;

public class SlowPU : MonoBehaviour
{
    private BlackholeMovement blackhole;

    private void Start()
    {
        blackhole = FindObjectOfType<BlackholeMovement>();//sets the blackhole variable
    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")//if the powerup collides with the player
        {
            blackhole.pausePowerup();//run the PausePowerup method.
            Destroy(gameObject);
        }
    }
}
