workspace(name = "com_github_volkszaehler_vzlogger")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# Load Prometheus and its dependencies
http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    strip_prefix = "prometheus-cpp-master",
    sha256 = "ff5509504dbfa29bea338fedc5f9482a20b245f6ea3f248824c2c63ecd6c9bee",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/master.zip"],
)
load("@com_github_jupp0r_prometheus_cpp//bazel:repositories.bzl", "prometheus_cpp_repositories")
prometheus_cpp_repositories()

# Other required dependencies by vzlogger
http_archive(
    name = "com_github_json-c_json-c",
    sha256 = "4ba9a090a42cf1e12b84c64e4464bb6fb893666841d5843cc5bef90774028882",
    strip_prefix = "json-c-json-c-0.15-20200726",
    urls = ["https://github.com/json-c/json-c/archive/json-c-0.15-20200726.tar.gz"]
)

# https://github.com/volkszaehler/libsml.git
http_archive(
    name = "com_github_volkszaehler_libsml",
    sha256 = "52ff770e11f875397fd3f4a9d61b11bbf0e9efb37b3ec15b958396717e1924cf",
    strip_prefix = "libsml-master",
    urls = ["https://github.com/volkszaehler/libsml/archive/master.zip"]
)

# https://github.com/rscada/libmbus.git
http_archive(
    name = "com_github_rscada_libmbus",
    sha256 = "6d98b5877e1fe7ed389a6ff095c70b9bbb1f16f0c1da27c94b6d974016b12a50",
    strip_prefix = "libmbus-master",
    urls = ["https://github.com/rscada/libmbus/archive/master.zip"]
)

# https://github.com/tesseract-ocr/tesseract/archive/4.1.1.zip
http_archive(
    name = "com_github_tesseract-ocr_tesseract",
    sha256 = "a2844da0112797b2ebafd58dfd011470b7d67d94fcf19f70627ddeb9b894391f",
    strip_prefix = "tesseract-4.1.1",
    urls = ["https://github.com/tesseract-ocr/tesseract/archive/4.1.1.zip"]
)
