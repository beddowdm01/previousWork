/*Script for the fastforward powerup*/
using UnityEngine;

public class FastForwardPU : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")// if collision was player call the players fastforward method
        {
            PlayerMovement.Instance.FastForward();
            Destroy(gameObject);
        }
    }
}
