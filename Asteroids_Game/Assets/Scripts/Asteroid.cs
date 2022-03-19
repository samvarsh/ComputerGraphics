using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Asteroid : MonoBehaviour
{
    public Sprite[] sprites;
    public float size = 1.0f;
    public float minSize = 0.5f;
    public float maxSize = 1.5f;
    public float speed = 50.0f;
    public float maxLifetime = 30.0f;
    private SpriteRenderer spriteRenderer;
    private Rigidbody2D rigidBody;

    public void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        rigidBody = GetComponent<Rigidbody2D>();
    }

    // Start is called before the first frame update
    private void Start()
    {
        // random ppty when it starts
        spriteRenderer.sprite = sprites[Random.Range(0, sprites.Length)];
        // randome.value = value between 0 and 1
        this.transform.eulerAngles = new Vector3(0.0f, 0.0f, Random.value * 360.0f);

        this.transform.localScale = Vector3.one * this.size;
        rigidBody.mass = this.size; // this  ll determine how fast or slow the asterooid ll be moving - bassed on the mass
    }

    // the spawner ll call this - just like the Player called Project()
    public void SetTrajectory(Vector2 direction)
    {
        rigidBody.AddForce(direction * this.speed);

        Destroy(this.gameObject, this.maxLifetime);
    }

    // Asteroids breaking on collision
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Bullet")
        {
            // split it if it is big enough
            if((this.size * 0.5f) >= this.minSize)
            {
                CreateSplit();
                CreateSplit();
            }

            FindObjectOfType<GameManager>().AsteroidDestroyed(this);
            Destroy(this.gameObject);
        }
    }

    private void CreateSplit()
    {
        Vector2 position = this.transform.position;
        position += Random.insideUnitCircle * 0.5f; // slight change of position after splitting

        Asteroid half = Instantiate(this, position, this.transform.rotation); 
        half.size = this.size * 0.5f;
        // give the split a random new trajectory
        half.SetTrajectory(Random.insideUnitCircle.normalized * this.speed); 

    }
}
