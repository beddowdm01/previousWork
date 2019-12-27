/*a powerup to stop blackhole movement for a short time*/
using UnityEngine;

public class SlowPU : MonoBehaviour
{
    private BlackholeMovement blackhole;

    private void Start()
    {
        blackhole = BlackholeMovement.Instance;

    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")//if the powerup collides with the player
        {
            blackhole.PausePowerup();//run the PausePowerup method.
            Destroy(gameObject);
        }
    }
}
