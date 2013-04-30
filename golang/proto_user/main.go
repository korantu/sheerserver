package main

import (
	"encoding/json"
	"flag"
	"log"
	"net"
	"net/http"
	"os"
	"runtime/debug"
)

// Niceties

func must_not(err error) {
	if err == nil {
		return
	}
	debug.PrintStack()
	log.Fatal(err.Error())
}

// Config

var tcp_port = "2845"

var users_config = "users.json"

// Data

type User struct {
	Id       string
	Password string
	Name     string
	Company  string
}

type Users struct {
	People []User
}


func (u *Users) Load() {
	users, err := os.Open("users.json")
	must_not(err)
	defer users.Close()

	people := Users{}

	decoder := json.NewDecoder(users)
	err = decoder.Decode(&people)
	must_not(err)

	for i, _ := range people.People {
		print(people.People[i].Name)
		print("\n")
	}
}

func response(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("1"))
	print("Render started.\n")
}

func server_main() {
	print("Started server at the port 8080.\n")
	http.HandleFunc("/main", response)
	http.ListenAndServe(":8080", nil)
}

func client_main() {
	_, err := http.Get("http://localhost:8080/main")
	if nil != err {
		log.Fatal(err.Error())
	}
	print("Render requested.\n")
}

func handle_connection(c net.Conn) {
	print("Got connection")
	c.Close()
}

func server_tcp() {
	ln, err := net.Listen("tcp", ":" + tcp_port )
	must_not(err)
	for {
		conn, err := ln.Accept()
		must_not(err)
		handle_connection(conn)
	}
}

func client_tcp() {
	net.Dial("tcp", "localhost:" + tcp_port)
}

func do_test() {
	users, err := os.Create(users_config)
	must_not(err)
	defer users.Close()

	people := Users{[]User{
		User{"123456", "24", "The Greatest", "SheerIndustries"},
		User{"654321", "42", "Yet Another User", "Self"},
	}}

	out := json.NewEncoder(users)
	err = out.Encode(people)
	must_not(err)

	u := Users{};
	u.Load();
}

func main() {
	tcp := flag.Bool("tcp", false, "use TCP")
	server := flag.Bool("server", false, "Start server")
	client := flag.Bool("client", false, "Start client")
	test := flag.Bool("test", false, "Check things")
	flag.Parse()
	switch {
	case *server:
		if *tcp {
			server_tcp()
		} else {
			server_main()
		}
	case *client:
		if *tcp {
			client_tcp()
		} else {
			client_main()
		}
	case *test:
		do_test()
	}
}
