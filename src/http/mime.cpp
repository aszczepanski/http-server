#include "http/mime.h"

#include <string>
#include <map>
#include <stdexcept>

using http::Mime;

Mime& Mime::GetInstance() {
  static Mime mime;
  return mime;
}

// TODO(adam): move values to config file
Mime::Mime() {
  mime_types_["js"] = "application/javascript";
  mime_types_["pdf"] = "application/pdf";
  mime_types_["xml"] = "application/xml";
  mime_types_["zip"] = "application/zip";

  mime_types_["mp4"] = "audio/mp4";
  mime_types_["mp3"] = "audio/mpeg";
  mime_types_["ogg"] = "audio/ogg";
  mime_types_["wav"] = "audio/vnd.wave";
  mime_types_["wave"] = "audio/vnd.wave";

  mime_types_["gif"] = "image/gif";
  mime_types_["ico"] = "image/vnd.microsoft.icon";
  mime_types_["jpeg"] = "image/jpeg";
  mime_types_["jpg"] = "image/jpeg";
  mime_types_["png"] = "image/png";

  mime_types_["css"] = "text/css";
  mime_types_["csv"] = "text/csv";
  mime_types_["html"] = "text/html";

  mime_types_["mp4"] = "video/mp4";
}

std::string Mime::GetType(const std::string& extension) {
  std::string mime_type;
  try {
    mime_type = mime_types_.at(extension);
  }
  catch (std::out_of_range&) {
    mime_type = "text/plain";
  }
  return mime_type;
}
