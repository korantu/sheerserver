package cloud

import (
	"io"
	"log"
	"net/http"
	"runtime/debug"
	//	"html/template"
	"io/ioutil"
	"os"
	"fmt"
	"bytes"
)

var port = "8080"

func must_not(err error) {
	if err == nil {
		return
	}
	debug.PrintStack()
	log.Fatal(err.Error())
}

func read_ui() []byte {
	str, err := ioutil.ReadFile("ui.html")
	must_not(err)
	return str
}

type InfoResponder struct {}
func ( i InfoResponder ) ServeHTTP (w http.ResponseWriter, r * http.Request ) {
	incoming, err := ioutil.ReadAll(r.Body)
	must_not( err)
	io.WriteString( w, "Request to: " + r.URL.String() + " \n")
	for key, values := range r.Header {
		for _, value := range values {
			io.WriteString(w, key + ":" + value + "\n")
		}
	}
	io.WriteString(w, "Input:--[" + string(incoming) + "]--\n")
}  

func Serve() {
	http.Handle("/info", InfoResponder{} )
	go http.ListenAndServe(":"+port, nil)

}

func body( resp * http.Response) []byte{
	data, err := ioutil.ReadAll(resp.Body)
	must_not( err)
	resp.Body.Close()
	return data
}

func Get( point string) []byte {
	resp, err := http.Get("http://localhost:8080/" + point)
	must_not( err)
	return body( resp)
}

func Post( point string, to_post []byte) []byte{
	resp, err := http.Post("http://localhost:8080/" + point, "application/octet-stream", bytes.NewReader( to_post))
	must_not( err)
	return body( resp)
}

func Main() {

	handlers := map[string] http.HandlerFunc {
		"/info.*": func(w http.ResponseWriter, r *http.Request) {

			say := func(msg string) {
				io.WriteString(w, msg+"\n")
				print(msg + "\n")
			}

			f,_, err := r.FormFile("model")
			if err != nil {
				say ( err.Error())
			} else {
				file, err := os.Create("out.tmp")
				if ( err != nil ) {
					say( err.Error())
				} else {
					defer file.Close()
					n, err := io.Copy( file, f)
					if ( err != nil ){
						say( err.Error())
					} else {
						say( fmt.Sprint( "Got ", n, " bytes."))
					}
				}
			}

			say("Incoming: " + r.URL.String())
			for key, values := range r.Header {
				for _, value := range values {
					say(key + ":" + value)
				}
			}			
		},
		"/ui": func(w http.ResponseWriter, r *http.Request) {
			w.Write(read_ui())
		},
	}

	for what, how := range handlers {
		http.HandleFunc( what, how );
	};

	print("Starting the server at port " + port + "\n")
	err := http.ListenAndServe(":"+port, nil)
	must_not(err)
}
