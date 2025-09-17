package call_back_funcs_for_requests
import (
	"net/http"

	//	"database/sql"
	_ "github.com/mattn/go-sqlite3"

	"github.com/gin-gonic/gin"
)

func Test_socket(c *gin.Context) {
	c.HTML(http.StatusOK, "showinformation.html", nil)

}
