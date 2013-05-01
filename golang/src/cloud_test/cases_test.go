package cloud_test

import (
	"cloud"
	"strings"
	"testing"
	"time"
)

func init() {
	print("Starting test server...\n")
	go cloud.Serve()
	time.Sleep(100 * time.Millisecond)
	print("Done.\n")
}

func Must(t *testing.T, be_true bool, reason string) {
	if !be_true {
		t.Log(reason)
		t.Fail()
	}
}

func TestSimplePostGet(t *testing.T) {
	cloud.Ping()
	post_resp := string(cloud.Post("info", []byte("ABC123")))
	get_resp := string(cloud.Get("info?a=1&a=2&b=3"))
	t.Log(post_resp)
	t.Log(get_resp)
	Must(t, strings.Contains(post_resp, "[ABC123]"), "Echo back posted file")
	Must(t, strings.Contains(get_resp, "b:3"), "Parse single parameters")
	Must(t, strings.Contains(get_resp, "a:1|2"), "Parse multiple parameters")
}

func TestUsers(t *testing.T) {
	u := cloud.User{Login: "abc", Password: "123", Name: "Me"}
	cloud.AddUser(&u)
	u1 := cloud.GetUser("abc", "123")
	Must(t, u.Name == u1.Name, "Get the same user")
}
