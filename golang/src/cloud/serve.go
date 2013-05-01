package cloud

import (
	"bytes"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"runtime/debug"
)

// TODO remove
var port = "8080"

// For autocomplete tests, does not usually work.
func Ping() bool {
	return true
}

// Niceties
func must_not(err error) {
	if err == nil {
		return
	}
	debug.PrintStack()
	log.Fatal(err.Error())
}

// Handlers
func info(w http.ResponseWriter, r *http.Request) {

	say := func(msg string) {
		io.WriteString(w, msg)
	}

	list_params := func(in map[string][]string) {
		for key, values := range in {
			say(key + ":")
			for i, value := range values {
				if i != 0 {
					say("|")
				}
				say(value)
			}
			say("\n")
		}
	}

	// Main response:
	incoming, err := ioutil.ReadAll(r.Body) // Must read body first
	must_not(err)
	in_url := r.URL.String()
	say("Request to: " + in_url + " \n")
	list_params(r.URL.Query())
	say("Headers:\n")
	list_params(r.Header)
	say("Input:--[" + string(incoming) + "]--\n")
}

func authorize(w http.ResponseWriter, r *http.Request) {
	say := func(msg string) {
		io.WriteString(w, msg)
	}

	param := r.URL.Query()
	login := param["login"]
	password := param["password"]
	u := GetUser( login[0], password[0])
	if u != nil {
		say( "OK")
	} else {
		say( "FAIL")
	}
}

// Server
func Serve() {
	http.HandleFunc("/info", info)
	http.HandleFunc("/authorize", authorize)
	go http.ListenAndServe(":"+port, nil)

}

// Client
func body(resp *http.Response) []byte {
	data, err := ioutil.ReadAll(resp.Body)
	must_not(err)
	resp.Body.Close()
	return data
}

func Get(point string) []byte {
	resp, err := http.Get("http://localhost:8080/" + point)
	must_not(err)
	return body(resp)
}

func Post(point string, to_post []byte) []byte {
	resp, err := http.Post("http://localhost:8080/"+point, "application/octet-stream", bytes.NewReader(to_post))
	must_not(err)
	return body(resp)
}

// Convinient API
type Identity struct {
	Login    string
	Password string
}

func (i Identity) Authorize() string {
	return string(Get("authorize?login=" + i.Login + "&password=" + i.Password))
}
