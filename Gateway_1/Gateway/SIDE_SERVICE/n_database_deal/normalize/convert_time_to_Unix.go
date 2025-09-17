package normalize

import (
	"time"
)

func Convert_from_time_to_unix_form() int64 {
	current_time_unix := time.Now().Unix()

	return current_time_unix

}
