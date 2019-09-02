/*Handles all camera movement within the game*/
using UnityEngine;

public class CameraMovement : MonoBehaviour
{

    public float zoomOut;
    public float xOffset = 15;
    public float yOffset = 0;
    public float timer = 0.25f;

    private bool finishedCount = false;
    private bool shaking = false;//for camera shake
    private Vector3 camOffset;//camera offset from the player
    private PlayerControls player;

    // Update is called once per frame

    private void Start()
    {
        player = FindObjectOfType<PlayerControls>();
    }

    void Update()
    {
        if (player != null) //if the player game object is active
        {
            camOffset = new Vector3(player.transform.position.x + xOffset, yOffset, zoomOut);
            transform.position = camOffset;
        }
        else if (shaking == true && finishedCount == false) //if camera needs to be shook
        {
            camOffset = new Vector3(xOffset + Random.Range(-0.5f, 0.5f), yOffset + Random.Range(-0.5f, 0.5f), zoomOut);//keep creating a random vector to shake the camera
            transform.position = camOffset;
            timer -= Time.unscaledDeltaTime;

            if (timer <= 0 && finishedCount == false)
            {
                finishedCount = true;

            }
        }


    }

    public void Shake()//method to shake the camera
    {
        shaking = true;
        xOffset = transform.position.x;//locks the cameras position
        yOffset = transform.position.y;
    }
}
