using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public bool InputsEnabled = true;
    public static PlayerMovement Instance;

    [SerializeField]
    private float sidewaysForce = 900f;
    [SerializeField]
    private float boostForce = 2000f;
    [SerializeField]
    private float maxSpeed = 65f;

    [SerializeField]
    private Rigidbody2D rb = null;

    private bool shouldSwapGravity = false;

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

    void Update()
    {
        MovementInputs();//Gets All the inputs
    }

    void FixedUpdate()//Fixed update for physics calculations
    {
        if (rb.velocity.x < maxSpeed)
        {
            rb.AddForce(new Vector2((sidewaysForce * (1 - (rb.velocity.x / 75))) * Time.deltaTime, 0f), ForceMode2D.Force);
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {

        }
        if (shouldSwapGravity)
        { //gravity up
            Physics2D.gravity = -Physics2D.gravity;
            rb.velocity = new Vector2(rb.velocity.x, (rb.velocity.y / 2));
            AudioManager.Instance.Play("upSound");
            shouldSwapGravity = false;
        }
    }

    private void MovementInputs()
    {
        if (Input.GetKeyDown(KeyCode.Space) && InputsEnabled)
        {
            shouldSwapGravity = true;
        }
    }


    public void FastForward()
    {
        rb.AddForce(new Vector2(boostForce, 0f), ForceMode2D.Force);
    }

}
