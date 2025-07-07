#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#endif

static void mkdir_if_needed(const char *path) {
    if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
}

// Utility: write a file with content, error-checking
static void write_file(const char *filepath, const char *content) {
    FILE *f = fopen(filepath, "w");
    if (!f) {
        perror(filepath);
        exit(EXIT_FAILURE);
    }
    fputs(content, f);
    fclose(f);
}

void generate_project_by_language(int lang_index, const char *project_name) {
    switch(lang_index) {
        case 0: generate_c_project(project_name); break;
        case 1: generate_cpp_project(project_name); break;
        case 2: generate_python_project(project_name); break;
        case 3: generate_go_project(project_name); break;
        case 4: generate_rust_project(project_name); break;
        case 5: generate_java_project(project_name); break;
        case 6: generate_nodejs_project(project_name); break;
        case 7: generate_typescript_project(project_name); break;
        case 8: generate_shell_project(project_name); break;
        case 9: generate_web_project(project_name); break;
        case 10: generate_lua_project(project_name); break;
        case 11: generate_haskell_project(project_name); break;
        default:
            fprintf(stderr, "Unknown language index %d\n", lang_index);
            exit(EXIT_FAILURE);
    }
}

// ========== C ==========
void generate_c_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.c", project_name);
    write_file(path,
        "#include <stdio.h>\n\n"
        "int main() {\n"
        "    printf(\"Hello, C world!\\n\");\n"
        "    return 0;\n"
        "}\n");

    snprintf(path, sizeof(path), "%s/Makefile", project_name);
    write_file(path,
        "all:\n"
        "\tgcc main.c -o main\n"
        "clean:\n"
        "\trm -f main\n");

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "main\n");
}

// ========== C++ ==========
void generate_cpp_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.cpp", project_name);
    write_file(path,
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Hello, C++ world!\" << std::endl;\n"
        "    return 0;\n"
        "}\n");

    snprintf(path, sizeof(path), "%s/Makefile", project_name);
    write_file(path,
        "all:\n"
        "\tg++ main.cpp -o main\n"
        "clean:\n"
        "\trm -f main\n");

    snprintf(path, sizeof(path), "%s/CMakeLists.txt", project_name);
    write_file(path,
        "cmake_minimum_required(VERSION 3.0)\n"
        "project(MyProject)\n"
        "add_executable(main main.cpp)\n");

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "main\n");
}

// ========== Python ==========
void generate_python_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.py", project_name);
    write_file(path,
        "def main():\n"
        "    print(\"Hello, Python world!\")\n\n"
        "if __name__ == \"__main__\":\n"
        "    main()\n");

    snprintf(path, sizeof(path), "%s/requirements.txt", project_name);
    write_file(path, "# Add your Python dependencies here\n");

    // Optionally create venv folder placeholder (empty dir)
    snprintf(path, sizeof(path), "%s/venv", project_name);
    mkdir_if_needed(path);
}

// ========== Go ==========
void generate_go_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.go", project_name);
    write_file(path,
        "package main\n\n"
        "import \"fmt\"\n\n"
        "func main() {\n"
        "    fmt.Println(\"Hello, Go world!\")\n"
        "}\n");

    snprintf(path, sizeof(path), "%s/go.mod", project_name);
    char mod_content[512];
    snprintf(mod_content, sizeof(mod_content), "module %s\n\ngo 1.20\n", project_name);
    write_file(path, mod_content);

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "bin\nvendor\n");
}

// ========== Rust ==========
void generate_rust_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    // Create src folder
    snprintf(path, sizeof(path), "%s/src", project_name);
    mkdir_if_needed(path);

    // main.rs
    snprintf(path, sizeof(path), "%s/src/main.rs", project_name);
    write_file(path,
        "fn main() {\n"
        "    println!(\"Hello, Rust world!\");\n"
        "}\n");

    // Cargo.toml
    snprintf(path, sizeof(path), "%s/Cargo.toml", project_name);
    char cargo_toml[512];
    snprintf(cargo_toml, sizeof(cargo_toml),
        "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n",
        project_name);
    write_file(path, cargo_toml);

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "target\n");
}

// ========== Java ==========
void generate_java_project(const char *project_name) {
    mkdir_if_needed(project_name);

    // Create folder structure: src/main/java
    char path[512];
    snprintf(path, sizeof(path), "%s/src/main/java", project_name);
    mkdir_if_needed(path);

    snprintf(path, sizeof(path), "%s/src/main/java/Main.java", project_name);
    write_file(path,
        "public class Main {\n"
        "    public static void main(String[] args) {\n"
        "        System.out.println(\"Hello, Java world!\");\n"
        "    }\n"
        "}\n");

    // pom.xml (basic Maven pom)
    snprintf(path, sizeof(path), "%s/pom.xml", project_name);
    write_file(path,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<project xmlns=\"http://maven.apache.org/POM/4.0.0\"\n"
        "         xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
        "         xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0\n"
        "                             http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n"
        "    <modelVersion>4.0.0</modelVersion>\n"
        "    <groupId>com.example</groupId>\n"
        "    <artifactId>MyProject</artifactId>\n"
        "    <version>1.0-SNAPSHOT</version>\n"
        "</project>\n");

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "target\n");
}

// ========== JavaScript (Node.js) ==========
void generate_nodejs_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/index.js", project_name);
    write_file(path,
        "console.log('Hello, Node.js world!');\n");

    snprintf(path, sizeof(path), "%s/package.json", project_name);
    char pkgjson[1024];
    snprintf(pkgjson, sizeof(pkgjson),
        "{\n"
        "  \"name\": \"%s\",\n"
        "  \"version\": \"1.0.0\",\n"
        "  \"main\": \"index.js\",\n"
        "  \"scripts\": {\n"
        "    \"start\": \"node index.js\"\n"
        "  },\n"
        "  \"dependencies\": {}\n"
        "}\n",
        project_name);
    write_file(path, pkgjson);

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "node_modules\n");
}

// ========== TypeScript ==========
void generate_typescript_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/index.ts", project_name);
    write_file(path,
        "console.log('Hello, TypeScript world!');\n");

    snprintf(path, sizeof(path), "%s/tsconfig.json", project_name);
    write_file(path,
        "{\n"
        "  \"compilerOptions\": {\n"
        "    \"target\": \"ES6\",\n"
        "    \"module\": \"commonjs\",\n"
        "    \"strict\": true,\n"
        "    \"esModuleInterop\": true\n"
        "  }\n"
        "}\n");

    snprintf(path, sizeof(path), "%s/package.json", project_name);
    char pkgjson[1024];
    snprintf(pkgjson, sizeof(pkgjson),
        "{\n"
        "  \"name\": \"%s\",\n"
        "  \"version\": \"1.0.0\",\n"
        "  \"main\": \"index.js\",\n"
        "  \"scripts\": {\n"
        "    \"build\": \"tsc\",\n"
        "    \"start\": \"node index.js\"\n"
        "  },\n"
        "  \"dependencies\": {},\n"
        "  \"devDependencies\": {\n"
        "    \"typescript\": \"^4.0.0\"\n"
        "  }\n"
        "}\n",
        project_name);
    write_file(path, pkgjson);

    snprintf(path, sizeof(path), "%s/.gitignore", project_name);
    write_file(path, "node_modules\n");
}

// ========== Shell ==========
void generate_shell_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.sh", project_name);
    write_file(path,
        "#!/bin/bash\n"
        "echo \"Hello, shell world!\"\n");
    // Make executable
#ifdef _WIN32
    // no chmod on Windows, user must do manually
#else
    chmod(path, 0755);
#endif
}

// ========== HTML/CSS/JS (web) ==========
void generate_web_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/index.html", project_name);
    write_file(path,
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "  <meta charset=\"UTF-8\">\n"
        "  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
        "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "  <title>Hello Web</title>\n"
        "  <link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
        "<body>\n"
        "  <h1>Hello, web world!</h1>\n"
        "  <script src=\"script.js\"></script>\n"
        "</body>\n"
        "</html>\n");

    snprintf(path, sizeof(path), "%s/style.css", project_name);
    write_file(path,
        "body {\n"
        "  font-family: Arial, sans-serif;\n"
        "  background: #f0f0f0;\n"
        "  color: #333;\n"
        "}\n");

    snprintf(path, sizeof(path), "%s/script.js", project_name);
    write_file(path,
        "console.log('Hello, web world!');\n");
}

// ========== Lua ==========
void generate_lua_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/main.lua", project_name);
    write_file(path,
        "print(\"Hello, Lua world!\")\n");
}

// ========== Haskell ==========
void generate_haskell_project(const char *project_name) {
    mkdir_if_needed(project_name);

    char path[512];
    snprintf(path, sizeof(path), "%s/Main.hs", project_name);
    write_file(path,
        "main :: IO ()\n"
        "main = putStrLn \"Hello, Haskell world!\"\n");

    snprintf(path, sizeof(path), "%s/stack.yaml", project_name);
    write_file(path,
        "resolver: lts-18.0\n");

    // Alternatively, a minimal cabal file could be created if preferred.
}
