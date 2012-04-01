/* tests */

/*
 * Connection configurations
 */
var settings = JSON.parse(require('fs').readFileSync('./tests/db_conf.json','utf8'));

/*
 * Create an Informix database nodejs object
 */
var informix = require("../nodejs-db-informix");

/*
 * Create a new Informix database bindings. Setup event callbacks. Connect to
 * the database.
 * c - connection
 */
var c = new informix.Binding(settings);
c.on('error', function(error) {
    console.log("Error: ");
    console.log(error);
}).on('ready', function(server) {
    console.log("Connected to ");
    console.log(server);
}).connect(function(err) {
    if (err) {
        throw new Error('Could not connect to DB');
    }
    console.log('Connected to db with ');
    console.log(settings);
    console.log("isConnected() == " + c.isConnected());

    // console.log(c);
    // var q = "select * from customer order by customer_num";
    var q = "select * from units order by unit_name";
    var rs = this.query(q
        , []
        , {
            start: function(q) {
                console.log(q);
            }
            , async: false
            , cast: false
            , each: function(r) {
                console.log("XXXX");
                console.log(r);
            }
        }).execute();

    /*
    var rs = c.query().select("*").from("foo").execute({
        start: function (q) {
            console.log (q);
        }
       , async : false
    });
    */
    console.log('Result set: ');
    console.log(rs);


    q = this.query(
          ""
        , []
        , {
            start: function(q) {
                console.log(q);
            }
            , async: true
            , cast: true
            , each: function(r) {
                console.log("XXXX");
                console.log(r);
            }
        }
        ).select("*").from("units", false).orderby("unit_name").execute();
});



/*
var tests = require("./tests_base.js").get(function(callback) {
    new informix.Database(settings).connect(function(err) {
        if (err) {
            throw new Error('Could not connect to test DB');
        }
        console.log('Connected to db with ' + settings);
        callback(this);
    });
});

// console.log (tests);

for(var test in tests) {
    console.log(test);
    exports[test] = tests[test];
}
*/
