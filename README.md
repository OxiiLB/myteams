Protocol MyTeams

use TCP protocol to communicate

The following are the mandatory FTP commands from client to server:

            /login "username\v"           : Specify user for authentication
            /logout "\v"                  : Logout

            CWD  <SP> <pathname> <CRLF>   : Change working directory
            CDUP <CRLF>                   : Change working directory to parent directory

            QUIT <CRLF>                   : Disconnection

            DELE <SP> <pathname> <CRLF>   : Delete file on the server

            PWD  <CRLF>                   : Print working directory

            PASV <CRLF>                   : Enable "passive" mode for data transfer

            PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer


            HELP [<SP> <string>] <CRLF>   : List available commands

            NOOP <CRLF>                   : Do nothing

            (the following are commands using data transfer )

            RETR <SP> <pathname> <CRLF>   : Download file from server to client
            STOR <SP> <pathname> <CRLF>   : Upload file from client to server
            LIST [<SP> <pathname>] <CRLF> : List files in the current working directory 


Command-Reply Sequences (Mandatory part)

The server reply contains a string with the 3-digit code, followed by "|", 
followed by one line of argument separated by "\n", each argument separated 
by a "\a", and terminated with "\v".

Example : (all strings)

-> : Request command from client to server
<- : Reply from server to client

-> /help
<- "200|COMMAND\nUSAGE-MESSAGE\n\v"

-> /login "username\v"
<- "200|COMMAND\nUSER-UUID\aUSER-NAME\n\v"

-> /logout "\v"
<- "200|COMMAND\nUSER-UUID\aUSER-USERNAME\n\v"

-> /users "\v"
<- "200|COMMAND\n
      [USER1-STATUS\aUSER1-UUID\aUSER1-NAME\n
      USER2-STATUS\aUSER2-UUID\aUSER2-NAME\n]\v"

-> /user "user-uuid\v"
<- "200|COMMAND\nUSER-STATUS\aUSER1-UUID\aUSER1-NAME\aUSER...\n\v"

-> /send "user-uuid\v" "messsage-body\v"
<- "200|COMMAND\nUSER-UUID\aUSER-MESSAGE\n\v"

-> /messages "user-uuid\v"
<- "200|COMMAND\n
      [SENDER1-UUID\aMESSAGE1-TIMESTAMP\aSENDER1-MESSAGE\n
      SENDER2-UUID\aMESSAGE2-TIMESTAMP\aSENDER2-MESSAGE\n]\v"

-> /subscribe "team-uuid\v"
<- "200|COMMAND\nUSER-UUID\aTEAM-UUID\n\v"


/subscribed "\v" -> CONTEXT = teams
/subscribed "team_uuid\v" -> CONTEXT = users

-> /subscribed "\v"
<- "200|COMMAND\nCONTEXT\n
      [TEAM1-UUID\aTEAM1-NAME\aTEAM1-DESCRIPTION\n
      TEAM2-UUID\aTEAM2-NAME\aTEAM2-DESCRIPTION\n]\v"

-> /subscribed "team_uuid\v"
<- "200|COMMAND\nCONTEXT\n
      [USER1-STATUS\aUSER1-UUID\aUSER1-NAME\n
      USER2-STATUS\aUSER2-UUID\aUSER2-NAME\n]\v"


-> /unsubscribe "team-uuid\v"
<- "200|COMMAND\nUSER-UUID\aTEAM-UUID\n\v"


/use "\v" -> CONTEXT = team
/use  “team_uuid” -> CONTEXT = channel
/use  “team_uuid” “channel_uuid” -> CONTEXT = thread
/use  “team_uuid” “channel_uuid” “thread_uuid” -> CONTEXT = reply

-> /create “team_name\v” “team_description\v”
<- "200|COMMAND\nCONTEXT\nTEAM-UUID\aTEAM-NAME\aTEAM-DESCRIPTION\n\v"

-> /create “channel_name\v” “channel_description\v”
<- "200|COMMAND\nCONTEXT\nCHANNEL-UUID\aCHANNEL-NAME\aCHANNEL-DESCRIPTION\n\v"

-> /create “thread_title\v” “thread_body\v”
<- "200|COMMAND\nCONTEXT\nTHREAD-UUID\aUSER-UUID\aTHREAD-TIMESTAMP\aTHREAD-TITLE\aTHREAD-BODY\n\v"

-> /create “comment_body\v”
<- "200|COMMAND\nCONTEXT\nTEAM-UUID\aTHREAD-UUID\aUSER-UUID\aREPLY-TIMESTAMP\aREPLY-BODY\n\v"

-> /list "\v" (if context is team)
<- "200|COMMAND\nCONTEXT\n
      [TEAM-UUID\aTEAM-NAME\aTEAM-DESCRIPTION\n
      TEAM-UUID2\aTEAM-NAME2\aTEAM-DESCRIPTION2\n]\v"

-> /list "\v" (if context is channel)
<- "200|COMMAND\nCONTEXT\n
      [CHANNEL-UUID\aCHANNEL-NAME\aCHANNEL-DESCRIPTION\n
      CHANNEL-UUID2\aCHANNEL-NAME2\aCHANNEL-DESCRIPTION2\n]\v"

-> /list "\v" (if context is thread)
<- "200|COMMAND\nCONTEXT\n
      [THREAD-UUID\aUSER-UUID\aTHREAD-TIMESTAMP\aTHREAD-TITLE\aTHREAD-BODY\n
      THREAD-UUID2\aUSER-UUID2\aTHREAD-TIMESTAMP2\aTHREAD-TITLE2\aTHREAD-BODY2\n]\v"

-> /list "\v" (if context is reply)
<- "200|COMMAND\nCONTEXT\n
      [THREAD-UUID\aUSER-UUID\aREPLY-TIMESTAMP\aREPLY-BODY\n
      THREAD-UUID2\aUSER-UUID2\aREPLY-TIMESTAMP2\aREPLY-BODY2\n]\v"


/use "\v" -> CONTEXT = user
/use  “team_uuid” -> CONTEXT = team
/use  “team_uuid” “channel_uuid” -> CONTEXT = channel
/use  “team_uuid” “channel_uuid” “thread_uuid” -> CONTEXT = thread

-> /info "\v" (if context is user)
<- "200|COMMAND\nCONTEXT\nUSER-STATUS\aUSER-UUID\aUSER-NAME\n\v"

-> /info "\v" (if context is team)
<- "200|COMMAND\nCONTEXT\nTEAM-UUID\aTEAM-NAME\aTEAM-DESCRIPTION\n\v"

-> /info "\v" (if context is channel)
<- "200|COMMAND\nCONTEXT\nCHANNEL-UUID\aCHANNEL-NAME\aCHANNEL-DESCRIPTION\n\v"

-> /info "\v" (if context is thread)
<- "200|COMMAND\nCONTEXT\nTHREAD-UUID\aUSER-UUID\aTHREAD-TIMESTAMP\aTHREAD-TITLE\aTHREAD-BODY\n\v"


            Connection Established
               <- 220

            Login
               USER ->
                  <- 200
                  <- 500

            Logout
               /logout ->
                  <- 200
                  <- 500

            Users
               /users ->
                  <- 200
                  <- 500
            
            User
               /user ->
                  <- 200
                  <- 500
            
            Send
               /send ->
                  <- 200
                  <- 500

            Transfer parameters

            user action commands

            Informational commands
               /help ->
                  <- 200 // ok
                  <- xxx // error

            Miscellaneous commands

Numeric  Order List of Mandatory Reply Codes (Extract)

         120 Service ready in nnn minutes.
         125 Data connection already open; transfer starting.
         150 File status okay; about to open data connection.
         200 Command okay.
         214 Help message.
             On how to use the server or the meaning of a particular
             non-standard command.  This reply is useful only to the
             human user.
         220 Service ready for new user.
         221 Service closing control connection.
             Logged out if appropriate.
         226 Closing data connection.
             Requested file action successful (for example, file
             transfer or file abort).
         227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).
         230 User logged in, proceed.
         250 Requested file action okay, completed.
         257 "PATHNAME" created.
         331 User name okay, need password.
         332 Need account for login.
         500 Internal Server Error
         501 User not found {USER-UUID}
         502 Unauthorized action
         503 Already exist
         504 Unknown team {TEAM-UUID}
         505 Unknown channel {CHANNEL-UUID}
         506 Unknown thread {THREAD-UUID}

         xxx Error (RFC compliant)

