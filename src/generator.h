#ifndef GENERATOR_H
#define GENERATOR_H

void generate_project_by_language(int lang_index, const char *project_name);

// You can keep existing per-language generators too, if needed
void generate_c_project(const char *project_name);
void generate_cpp_project(const char *project_name);
void generate_python_project(const char *project_name);
void generate_go_project(const char *project_name);
void generate_rust_project(const char *project_name);
void generate_java_project(const char *project_name);
void generate_nodejs_project(const char *project_name);
void generate_typescript_project(const char *project_name);
void generate_shell_project(const char *project_name);
void generate_web_project(const char *project_name);
void generate_lua_project(const char *project_name);
void generate_haskell_project(const char *project_name);

#endif
