/*controls the colour of door indication arrows*/
using UnityEngine;

public class ArrowControls : MonoBehaviour
{
    public SpriteRenderer pic;
    public Sprite gArrow;
    public Sprite rArrow;

    // Update is called once per frame
    void FixedUpdate()//if gravity is facing a certain way change the arrows sprite
    {
        if (Physics2D.gravity.y > 0)
        {
            pic.sprite = rArrow;
        }
        if (Physics2D.gravity.y < 0)
        {
            pic.sprite = gArrow;
        }


    }
}
