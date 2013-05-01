package main

import (
	"cloud"
	"time"
)

// TODO: File unused so far, refer to cloud_test.
// Once functionality is tested, it will be moved here.

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
