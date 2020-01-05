/*Moves the shield sprite with the player*/
using UnityEngine;

public class ShieldMovement : MonoBehaviour
{
    private Quaternion fixedRotation;//the roatation of the shield

    private void Awake()
    {
        fixedRotation = transform.rotation;
    }


    private void LateUpdate()
    {
        transform.rotation = fixedRotation;
    }
}
