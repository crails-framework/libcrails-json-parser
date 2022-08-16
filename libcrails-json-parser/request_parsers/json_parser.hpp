#ifndef  CRAILS_JSON_PARSER_HPP
# define CRAILS_JSON_PARSER_HPP

# include <crails/request_parser.hpp>

namespace Crails
{
  class RequestJsonParser : public BodyParser
  {
  public:
   void operator()(Connection&, BuildingResponse&, Params&, std::function<void(RequestParser::Status)>) const override;
  private:
    void body_received(Connection&, BuildingResponse&, Params&, const std::string& body) const override;
  };
}

#endif
