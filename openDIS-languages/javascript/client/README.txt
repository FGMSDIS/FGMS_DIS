This is an "implementation" if DIS, for certain values of
"implementation." 

Since Javascript does not deal well with binary formats, 
this simply holds the semantic data in traditional
Javascript objects. Typically you'll pass this data
around in JSON format on the web. 

A typical use case will be to receive and send DIS
Javascript objects in JSON format over a websocket
from a server. The server side will convert the JSON
object to a Java object, then marshall it to DIS.


This is a pretty sleazy project done in an afternoon, so
don't expect nice code or anything.

DMcG
