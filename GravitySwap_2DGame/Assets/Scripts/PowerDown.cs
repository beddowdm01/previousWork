using UnityEngine;

public class PowerDown : MonoBehaviour
{
    public PlayerControls player;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            player.PowerDown();
            Destroy(gameObject);
        }
    }
}
