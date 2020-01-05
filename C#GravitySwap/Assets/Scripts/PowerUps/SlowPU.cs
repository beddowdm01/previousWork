/*a powerup to stop blackhole movement for a short time*/
using UnityEngine;

public class SlowPU : MonoBehaviour
{

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")//if the powerup collides with the player
        {
            BlackholeMovement.Instance.PausePowerup();//run the PausePowerup method.
            Destroy(gameObject);
        }
    }
}
