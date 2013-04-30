package main

import (
	"io"
	"log"
	"net/http"
	"runtime/debug"
	//	"html/template"
	"io/ioutil"
	"os"
	"fmt"
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

func main() {

	handlers := map[string] http.HandlerFunc {
		"/info": func(w http.ResponseWriter, r *http.Request) {

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
