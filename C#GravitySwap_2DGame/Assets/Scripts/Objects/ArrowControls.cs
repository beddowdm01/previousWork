/*controls the colour of door indication arrows*/
using UnityEngine;

public class ArrowControls : MonoBehaviour
{
    [SerializeField]
    private SpriteRenderer spriteRenderer = null;
    [SerializeField]
    private Sprite gArrow = null;
    [SerializeField]
    private Sprite rArrow = null;

    // Update is called once per frame
    void FixedUpdate()//if gravity is facing a certain way change the arrows sprite
    {
        if (Physics2D.gravity.y > 0)
        {
            spriteRenderer.sprite = rArrow;//if gravity is upwards
        }
        if (Physics2D.gravity.y < 0)
        {
            spriteRenderer.sprite = gArrow;//if gravity is downwards
        }


    }
}
