using UnityEngine;

public class PlayerCharacter : MonoBehaviour
{
    public static PlayerCharacter Instance;

    [SerializeField]
    private ParticleSystem electricfx = null;
    [SerializeField]
    private ParticleSystem blackholefx = null;
    [SerializeField]
    private GameObject shieldRenderer = null;

    private GameObject[] environmentObjects;
    private bool shielded = false;
    private SpriteRenderer spriteRenderer;

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
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.tag == "blackhole")
        {
            if (shielded == false)
            {
                AudioManager.Instance.Play("PlayerDeath");
                Destroy(gameObject);
                GameManager.Instance.EndGame();
                ParticleSystem atoms = Instantiate(blackholefx, transform.position, Quaternion.identity);
                CameraMovement.Instance.Shake();
            }
            else
            {
                RemoveShield();
            }
        }
        else if (collisionInfo.tag == "electricWall")
        {
            if (shielded == false)
            {
                AudioManager.Instance.Play("PlayerDeath");
                Destroy(gameObject);
                GameManager.Instance.EndGame();
                ParticleSystem sparks = Instantiate(electricfx, transform.position, Quaternion.identity);
                CameraMovement.Instance.Shake();
            }
            else
            {
                RemoveShield();
            }
        }
        else if (collisionInfo.tag == "mainBlackhole")
        {
            AudioManager.Instance.Play("PlayerDeath");
            Destroy(gameObject);
            GameManager.Instance.EndGame();
            ParticleSystem atoms = Instantiate(blackholefx, transform.position, Quaternion.identity);
            CameraMovement.Instance.Shake();
        }
    }

    public void Ghost()
    {
        spriteRenderer.color = new Color(spriteRenderer.color.r, spriteRenderer.color.g,spriteRenderer.color.b, 0.5f);
    }

    public void Unghost()
    {
        spriteRenderer.color = new Color(spriteRenderer.color.r, spriteRenderer.color.g, spriteRenderer.color.b, 1f);
    }

    public void Shield()
    {
        shielded = true;
        shieldRenderer.SetActive(true);
        Debug.Log("Shielded");
    }

    public void RemoveShield()
    {
        shielded = false;
        shieldRenderer.SetActive(false);
        Debug.Log("Unshielded");
    }
}
