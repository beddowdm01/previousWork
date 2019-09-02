using UnityEngine;

public class WavePowerUp : MonoBehaviour
{
    public PlayerControls player;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            player.WavePowerup();
            Destroy(gameObject);
        }
    }
}
