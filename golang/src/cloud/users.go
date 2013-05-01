package cloud

// User state
type User struct {
	Id int
	Name string
	Login string
	Password string
}

// Requests for adding/getting users
type Request struct{
	TheUser User
	Reply chan * User
}

// Interface channels
var AddUser = make(chan * Request)
var GetUser = make(chan * Request)

// Storage
var unused_id = 0
var by_id = make(map[int] * User)
var by_login = make(map[string] * User)

// Machinery; Not-thread-safe.
func add( a * User) * User {
	if a.Login == "" || a.Password == "" {
		return nil
	}
	a.Id = unused_id; unused_id++;
	
	by_id[a.Id] = a;
	by_login[a.Login] = a;

	return a;
};

// TODO: select


























