package cloud_test

import (
	"testing"
	"cloud"
	"time"
	"strings"
)

func init() {
	print("Starting test server...\n");
	go cloud.Serve()
	time.Sleep(100 * time.Millisecond)
	print("Done.\n")
}

type MyT testing.T
func Must ( t * testing.T, be_true bool, reason string ) {
	if ! be_true {
		t.Log( reason)
		t.Fail()
	}
}

func TestSimplePostGet( t * testing.T){
	cloud.Ping()
	post_resp := string(cloud.Post("info", []byte("ABC123")))
	get_resp := string(cloud.Get("info?a=1&a=2&b=3"))
	t.Log( post_resp)
	t.Log( get_resp)
	Must(t, strings.Contains(post_resp, "[ABC123]"), "Echo back posted file")
	Must(t, strings.Contains(get_resp, "b:3"), "Parse single parameters")
	Must(t, strings.Contains(get_resp, "a:1|2"), "Parse multiple parameters")
}


















