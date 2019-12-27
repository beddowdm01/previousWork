/*If the player reaches the end zone of the level*/
using UnityEngine;

public class EndCollision : MonoBehaviour
{
    public static EndCollision Instance;

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
            return;
        }
    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            GameManager.Instance.CompleteLevel();//runs the complete level method in the gamemanager
            Debug.Log("level complete");
        }
    }
}
