/*A class to moveobjects that are trapped in gravity bubbles*/
using UnityEngine;

public class ObjectMovement : MonoBehaviour
{

    public float xMovement = -0.03f;
    public float yMovement = 0f;

    void FixedUpdate()
    {
            transform.Translate(xMovement, yMovement, 0, Space.World);//Move the object.
    }
}
