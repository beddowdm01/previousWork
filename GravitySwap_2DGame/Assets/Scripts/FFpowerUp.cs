/*Script for the fastforward powerup*/
using UnityEngine;

public class FFpowerUp : MonoBehaviour
{
    private PlayerControls player;

    private void Start()//on start set player variable
    {
        player = FindObjectOfType<PlayerControls>();
    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")// if collision was player call the players fastforward method
        {
            player.FastForward();
            Destroy(gameObject);
        }
    }
}
