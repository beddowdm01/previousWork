using UnityEngine;

public class PlayerControls : MonoBehaviour
{
    public Rigidbody2D rb;
    public bool isDown = true;
    public Vector2 up = new Vector2(0f, 9.81f);
    public Vector2 down = new Vector2(0f, -9.81f);
    public float sidewaysForce = 900f;
    public float boostForce = 2000f;
    public float waveRange = 50f;
    public float respawnTimer = 4f;
    public ParticleSystem electricfx;
    public ParticleSystem blackholefx;

    private SpriteRenderer shieldPU;
    private GameObject[] environmentObjects;
    private bool shielded = false;

    private void Start()
    {
        Physics2D.gravity = down;
        shieldPU = FindObjectOfType<ShieldMovement>().GetComponent<SpriteRenderer>();
    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.tag == "blackhole")
        {
            if (shielded == false)
            {
                FindObjectOfType<AudioManager>().Play("PlayerDeath");
                Destroy(gameObject);
                FindObjectOfType<GameManager>().EndGame();
                ParticleSystem atoms = Instantiate(blackholefx, transform.position, Quaternion.identity);
                FindObjectOfType<CameraMovement>().Shake();
            }
            else
            {
                Unshield();
            }
        }
        else if (collisionInfo.tag == "electricWall")
        {
            if (shielded == false)
            {
                FindObjectOfType<AudioManager>().Play("PlayerDeath");
                Destroy(gameObject);
                FindObjectOfType<GameManager>().EndGame();
                ParticleSystem sparks = Instantiate(electricfx, transform.position, Quaternion.identity);
                FindObjectOfType<CameraMovement>().Shake();
            }
            else
            {
                Unshield();
            }
        }
        else if (collisionInfo.tag == "mainBlackhole")
        {
            FindObjectOfType<AudioManager>().Play("PlayerDeath");
            Destroy(gameObject);
            FindObjectOfType<GameManager>().EndGame();
            ParticleSystem atoms = Instantiate(blackholefx, transform.position, Quaternion.identity);
            FindObjectOfType<CameraMovement>().Shake();
        }
    }

    public void FastForward()
    {
        rb.AddForce(new Vector2(boostForce, 0f), ForceMode2D.Force);
    }

    public void WavePowerup()
    {
        environmentObjects = GameObject.FindGameObjectsWithTag("environment");
        for (int i = 0; i < environmentObjects.Length; i++)
        {
            if (Vector2.Distance(environmentObjects[i].transform.position, rb.position) < waveRange)
            {
                Destroy(environmentObjects[i]);
            }
        }
    }

    public void PowerDown()
    {
        rb.velocity = new Vector2(0, 0);
    }

    public void Ghost()
    {
        Color temp = gameObject.GetComponent<SpriteRenderer>().color;
        temp.a = 0.5f;
        gameObject.GetComponent<SpriteRenderer>().color = temp;
    }

    public void Unghost()
    {
        Color temp = gameObject.GetComponent<SpriteRenderer>().color;
        temp.a = 1f;
        gameObject.GetComponent<SpriteRenderer>().color = temp;
    }

    public void Shield()
    {
        shielded = true;
        shieldPU.enabled = true;
    }

    public void Unshield()
    {
        shielded = false;
        shieldPU.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (rb.velocity.x < 75)
        {
            rb.AddForce(new Vector2((sidewaysForce * ( 1 - (rb.velocity.x/75))) *Time.deltaTime, 0f), ForceMode2D.Force);
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (isDown == true && Time.timeScale == 1f)
            { //gravity up
                Physics2D.gravity = up;
                rb.velocity = new Vector2(rb.velocity.x, (rb.velocity.y / 2));
                isDown = false;
                FindObjectOfType<AudioManager>().Play("upSound");
            }
            else if (isDown == false && Time.timeScale == 1f)
            { //gravity down
                Physics2D.gravity = down;
                isDown = true;
                FindObjectOfType<AudioManager>().Play("downSound");
            }
        }
    }
}
