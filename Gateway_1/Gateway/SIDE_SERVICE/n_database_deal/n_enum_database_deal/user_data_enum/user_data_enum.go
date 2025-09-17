package user_data_enum

type User_data int

type User_data_string string

const Columns_length_defined = 9

const (
	ID_OF_USER           User_data = 0
	USERNAME_OF_USER     User_data = 1
	PASSWORD_OF_USER     User_data = 2
	ROLE_OF_USER         User_data = 3
	CREATED_AT_OF_USER   User_data = 4
	UPDATED_AT_OF_USER   User_data = 5
	FULL_NAME_OF_USER    User_data = 6
	PHONE_NUMBER_OF_USER User_data = 7
	EMAIL_OF_USER        User_data = 8
)

const (
	ID_OF_USER_CONST           User_data_string = "id"
	USERNAME_OF_USER_CONST     User_data_string = "username"
	PASSWORD_OF_USER_CONST     User_data_string = "password"
	ROLE_OF_USER_CONST         User_data_string = "role"
	CREATED_AT_OF_USER_CONST   User_data_string = "created_at"
	UPDATED_AT_OF_USER_CONST   User_data_string = "update_at"
	FULL_NAME_OF_USER_CONST    User_data_string = "full_name"
	PHONE_NUMBER_OF_USER_CONST User_data_string = "phone_number"
	EMAIL_OF_USER_CONST        User_data_string = "email"
)


var User_table_name = "user"





var User_array = []User_data_string{
	ID_OF_USER_CONST           ,
	USERNAME_OF_USER_CONST     ,
	PASSWORD_OF_USER_CONST     ,
	ROLE_OF_USER_CONST         ,
	CREATED_AT_OF_USER_CONST   ,
	UPDATED_AT_OF_USER_CONST   ,
	FULL_NAME_OF_USER_CONST    ,
	PHONE_NUMBER_OF_USER_CONST ,
	EMAIL_OF_USER_CONST        , 
}