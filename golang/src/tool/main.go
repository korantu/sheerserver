package main

import (
	"cloud"
	"time"
)

func test_get() {
	got := cloud.Get("info?a=b&c=d")
	print("\n---get---\n" + string(got) + "\n------\n")
}

func test_post() {
	got := cloud.Post("info", []byte("123"))
	print("\n---post---\n" + string(got) + "\n------\n")
}

func init() {
	go cloud.Serve()
	time.Sleep(100 * time.Millisecond)
}

func main() {
	test_get()
	test_post()
}
