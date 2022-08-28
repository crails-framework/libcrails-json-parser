#include <boost/property_tree/json_parser.hpp>
#include "json_parser.hpp"
#include <crails/context.hpp>

using namespace std;
using namespace Crails;
using namespace boost::property_tree;

void RequestJsonParser::operator()(Context& context, function<void(RequestParser::Status)> callback) const
{
  static const regex is_json("application/json", regex_constants::extended | regex_constants::optimize);
  const HttpRequest& request = context.connection->get_request();

  if (request.method() != HttpVerb::get && content_type_matches(request, is_json))
  {
    wait_for_body(context, [callback]()
    {
      callback(RequestParser::Stop);
    });
  }
  else
    callback(RequestParser::Continue);
}

void RequestJsonParser::body_received(Context& context, const string& body) const
{
  if (body.size() > 0)
    context.params.as_data().merge(DataTree().from_json(body));
}
