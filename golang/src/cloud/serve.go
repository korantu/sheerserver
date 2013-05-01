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
	"time"
)

var port = "8080"

func must_not(err error) {
	if err == nil {
		return
	}
	debug.PrintStack()
	log.Fatal(err.Error())
}

func say(w io.Writer, msg string) {
	io.WriteString(w, msg+"\n")
	print(msg + "\n")
}


func read_ui() []byte {
	str, err := ioutil.ReadFile("ui.html")
	must_not(err)
	return str
}

type ServeOnce struct {
	task http.Handler
	done chan bool
}
func ( s * ServeOnce ) ServeHTTP (w http.ResponseWriter, r * http.Request ) {
	s.task.ServeHTTP(w, r)
	s.done <- true
};

type InfoResponder struct {}
func ( i InfoResponder ) ServeHTTP (w http.ResponseWriter, r * http.Request ) {
	io.WriteString( w, "Request:\n")
	say( w, "Incoming: " + r.URL.String())
	for key, values := range r.Header {
		for _, value := range values {
			say( w, key + ":" + value)
		}
	}			
}  

func Serve( once bool) {
	done := make( chan bool )
	if once {
		http.Handle("/info", &ServeOnce{InfoResponder{}, done} )
	} else {
		http.Handle("/info", InfoResponder{} )
	}
	go http.ListenAndServe(":"+port, nil)
	<-done // If something is once.
	time.Sleep( time.Second) // To send responses.

}

func Get() {
	http.Get("http://localhost:8080/info?parameters")
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
