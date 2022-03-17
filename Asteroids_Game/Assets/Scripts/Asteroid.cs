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
}
