#include  <iostream>
#include <String>



using namespace std;
#include <winsqlite/winsqlite3.h>
#pragma comment(lib, "winsqlite3.lib")


int callback(void*, int argc, char** argv, char**) {
	for (int i = 0; i < argc; i++) {
		cout << (argv[i] ? argv[i] : "NULL") << " ";
	}
	cout << endl;
	return 0;
}



int main() {
	sqlite3* db;

	int rc = sqlite3_open("test_db_db.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error: Cannot open database" << endl;
		return 1;
	}

	const char* sql = "CREATE TABLE IF NOT EXIST users ("
	"id INTEGER PRIMARY KEY AUTOINCREMENT, "
	"username TEXT UNIQUE, "
	"password TEXT, "
	"display_name TEXT, "
	"email TEXT UNIQUE ) ";

	if (rc != SQLITE_OK) {
		sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
		return 1;
	}
	
	sql = "INSERT INTO users (username, password, email) VALUES ("
		"test, pass123123, qwertyuiop@example.com "
		"test123, 12345678, example123@example.com "
		"testtest, 123qwe123qwe, example@example.com ";

	if (rc != SQLITE_OK) {
		sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
		return 1;
	}

	sql = "SELECT * FROM users";

	if (rc != SQLITE_OK) {
		sqlite3_exec(db, sql, callback, nullptr, nullptr);
		return 1;
	}
}