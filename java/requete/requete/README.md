

Requete (Backend) uses MongoDB and MongoRepositories exposed via a hypermedia-based RESTful interface
mongod must be runnig with the default port (27017)

The service is available at http://localhost:8080/req
It has some options such as ?page, ?size, and ?sort.

Spring Data REST uses the HAL format for JSON output. 

To insert new objects:
curl -i -X POST -H "Content-Type:application/json" -d "{  \"source\" : \"Requirement\",  \"shortText\" : \"ShallDo\",  \"status\" : \"0\",  \"text\" : \"There is a requirement\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}" http://localhost:8080/req

From this you can query for all entries on req:
$ curl http://localhost:8080/req

You can query directly for the given record:
$ curl http://localhost:8080/req/53149b8e3004990b1af9f229

Find all the custom queries (only one findBySource):
$ curl http://localhost:8080/req/search

{
    "links": [
        {
            "rel": "findBySource",
            "href": "http://localhost:8080/req/search/findBySource{?name}"
        },
        {
            "rel": "self",
            "href": "http://localhost:8080/req/search"
        }
    ]
}

To use the findBySource query, do this:
$ curl http://localhost:8080/req/search/findBySource?name=Requirement

{
    "links": [
        {
            "rel": "self",
            "href": "http://localhost:8080/req/search/findBySource?name=Requirement%27s%20girl"
        }
    ],
    "content": [
        {
            "source": "Requirement",
            "shortText": "ShallDo",
            "status": "ENTERED",
            "text": "There is a requirement",
            "given": "a",
            "when": "b",
            "then": "c",
            "id": "5a2d81adca74361004735faa",
            "content": [],
            "links": [
                {
                    "rel": "self",
                    "href": "http://localhost:8080/req/5a2d81adca74361004735faa"
                },
                {
                    "rel": "req",
                    "href": "http://localhost:8080/req/5a2d81adca74361004735faa"
                }
            ]
        }
    ]
}

You can issue PUT, PATCH, and DELETE REST calls as well

PUT replaces an entire record. Not supplied fields will be replaced with null. 
PATCH can be used to update a subset of items.
DELETE: 
$ curl -X DELETE http://localhost:8080/req/53149b8e3004990b1af9f229
