/*Opens doors if gravity is facing a certain way*/
using UnityEngine;

public class Door : MonoBehaviour
{
    public float speed = 100f;
    public float openLimit = 35f;
    public bool reverse = false;//reverses the way gravity needs to be to open the door - default is down.

    private float beginLocY;

    private void Start()
    {
        beginLocY = transform.position.y;//sets the beginning location.
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (reverse == false)
        {
            if (Physics2D.gravity.y > 0 && transform.position.y <= (beginLocY + openLimit)) //if gravity up
            {
                transform.Translate(0, speed, 0);
            }
            else if (Physics2D.gravity.y < 0 && transform.position.y >= (beginLocY+speed))//if gravity down
            {
                transform.Translate(0, -speed, 0);
            }
        }
        if (reverse == true)
        {
            if (Physics2D.gravity.y > 0 && transform.position.y <= (beginLocY-speed)) //if gravity up
            {
                transform.Translate(0, speed, 0);
            }
            else if (Physics2D.gravity.y < 0 && transform.position.y >= (beginLocY - openLimit))//if gravity down
            {
                transform.Translate(0, -speed, 0);
            }
        }
    }
}
