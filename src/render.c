#include "global.h"
#include "util.h"
#include "io.h"
#include "render.h"
#include "stb_image.h"

typedef struct {
    uint32_t vao_quad;
    uint32_t vbo_quad;
    uint32_t ebo_quad;
    uint32_t shader_default;
    uint32_t texture_color;
    mat4x4 projection;
} Render_State_Internal;

static Render_State_Internal state = {0};

static SDL_Window *init_window(uint32_t width, uint32_t height);
static void init_quad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
static void init_shaders(Render_State_Internal *state);
static void init_color_texture(uint32_t *texture);

void render_init(void) {
    global.render.width = 800;
    global.render.height = 600;
    global.render.window = init_window(global.render.width, global.render.height);
    init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
    init_shaders(&state);
    init_color_texture(&state.texture_color);
}

void render_begin(void) {
	glClearColor(0.08, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(void) {
    SDL_GL_SwapWindow(global.render.window);
}

void render_quad(vec2 pos, vec2 size, vec4 color) {
    glUseProgram(state.shader_default);

    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(
        glGetUniformLocation(state.shader_default, "model"),
        1, GL_FALSE, &model[0][0]);

    glUniform4fv(
        glGetUniformLocation(state.shader_default, "color"),
        1, color);

    glBindVertexArray(state.vao_quad);

    glBindTexture(GL_TEXTURE_2D, state.texture_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}

uint32_t render_shader_create(const char *path_vert, const char *path_frag) {
    int success;
    char log[512];

    File file_vertex = io_file_read(path_vert);
    if (!file_vertex.is_valid)
        ERROR_EXIT("Error reading vertex shader: %s\n", path_vert);
    uint32_t shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, (const char *const *)&file_vertex, NULL);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_vertex, 512, NULL, log);
        ERROR_EXIT("Error compiling vertex shader. %s\n", log);
    }

    File file_fragment = io_file_read(path_frag);
    if (!file_fragment.is_valid)
        ERROR_EXIT("Error reading fragment shader: %s\n", path_frag);
    uint32_t shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragment, 1, (const char *const *)&file_fragment, NULL);
    glCompileShader(shader_fragment);
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_fragment, 512, NULL, log);
        ERROR_EXIT("Error compiling fragment shader. %s\n", log);
    }

    uint32_t shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_fragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, log);
        ERROR_EXIT("Error linking shader. %s\n", log);
    }

    free(file_vertex.data);
    free(file_fragment.data);

    return shader;
}






static SDL_Window *init_window(uint32_t width, uint32_t height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
        ERROR_EXIT("ERROR: Failed to initialize SDL: %s\n", SDL_GetError());

	SDL_Window *window = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, 
        SDL_WINDOW_OPENGL);

    if (!window)
        ERROR_EXIT("ERROR: Failed to initialize SDL: %s\n", SDL_GetError());

	/*SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");*/

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        ERROR_EXIT("ERROR: Failed to load GL: %s\n", SDL_GetError());

    printf("OpenGL version %s\n", glGetString(GL_VERSION));
    printf("\tVendor: %s\n", glGetString(GL_VENDOR));
    printf("\tRenderer: %s\n", glGetString(GL_RENDERER));

    return window;
}

static void init_quad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo) {
    //    x,    y, z,   u, v
    float vertices[] = {
        0.5,  0.5, 0,   0, 0,
        0.5, -0.5, 0,   0, 1,
       -0.5, -0.5, 0,   1, 1,
       -0.5,  0.5, 0,   1, 0
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // xyz
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


static void init_shaders(Render_State_Internal *state) {
    state->shader_default = render_shader_create("assets/shaders/default.vert", "assets/shaders/default.frag");

    mat4x4_ortho(state->projection, 0, global.render.width, 0, global.render.height, -2, 2);

    glUseProgram(state->shader_default);
    glUniformMatrix4fv(
        glGetUniformLocation(state->shader_default, "projection"),
        1,
        GL_FALSE,
        &state->projection[0][0]
    );
}

static void init_color_texture(uint32_t *texture) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    uint8_t white[4] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    glBindTexture(GL_TEXTURE_2D, 0);
}






/*SDL_Texture *load_texture(char *filename) {*/
    /*SDL_Surface *surface;*/
    /*SDL_Texture *texture;*/
    /*int texture_width, texture_height;*/
    /*unsigned char *texture_pixels;*/
    /*int color_format = STBI_rgb_alpha;*/

    /*printf("[INFO] Loading %s\n", filename);*/

    /*texture_pixels = stbi_load(filename, &texture_width, &texture_height, NULL, color_format);*/

    /*if(texture_pixels == NULL) {*/
        /*[>TODO(shaw): try to load a default texture if this one is not found<]*/
        /*fprintf(stderr, "[ERROR] Loading image %s failed: %s", filename, stbi_failure_reason());*/
        /*return NULL;*/
    /*}*/

    /*// Set up the pixel format color masks for RGB(A) byte arrays.*/
    /*Uint32 r_mask, g_mask, b_mask, a_mask;*/
/*#if SDL_BYTEORDER == SDL_BIG_ENDIAN*/
    /*int shift = (color_format == STBI_rgb) ? 8 : 0;*/
    /*r_mask = 0xff000000 >> shift;*/
    /*g_mask = 0x00ff0000 >> shift;*/
    /*b_mask = 0x0000ff00 >> shift;*/
    /*a_mask = 0x000000ff >> shift;*/
/*#else // little endian, like x86*/
    /*r_mask = 0x000000ff;*/
    /*g_mask = 0x0000ff00;*/
    /*b_mask = 0x00ff0000;*/
    /*a_mask = (color_format == STBI_rgb) ? 0 : 0xff000000;*/
/*#endif*/

    /*int depth, pitch;*/
    /*if (color_format == STBI_rgb) {*/
        /*depth = 24;*/
        /*pitch = 3*texture_width; // 3 bytes per pixel * pixels per row*/
    /*} else { // STBI_rgb_alpha (RGBA)*/
        /*depth = 32;*/
        /*pitch = 4*texture_width;*/
    /*}*/

    /*surface = SDL_CreateRGBSurfaceFrom(texture_pixels, texture_width, texture_height, */
        /*depth, pitch, r_mask, g_mask, b_mask, a_mask);*/

    /*if (surface == NULL) {*/
      /*fprintf(stderr, "Creating surface failed: %s", SDL_GetError());*/
      /*stbi_image_free(texture_pixels);*/
      /*return NULL;*/
    /*}*/

    /*texture = SDL_CreateTextureFromSurface(app.renderer, surface);*/

    /*SDL_FreeSurface(surface);*/
    /*stbi_image_free(texture_pixels);*/

    /*return texture;*/
/*}*/

/*void blit(SDL_Texture *texture, int x, int y) {*/
	/*SDL_Rect dest = {.x = x, .y = y};*/
	/*SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);*/
	/*SDL_RenderCopy(app.renderer, texture, NULL, &dest);*/
/*}*/

/*void blit_scaled(SDL_Texture *texture, int x, int y, int w, int h) {*/
	/*SDL_Rect dest = { .x = x, .y = y, .w = w, .h = h };*/
	/*SDL_RenderCopy(app.renderer, texture, NULL, &dest);*/
/*}*/

/*void blit_rect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {*/
	/*SDL_Rect dest = {*/
        /*.x = x,*/
        /*.y = y,*/
        /*.w = src->w,*/
        /*.h = src->h*/
    /*};*/
	/*SDL_RenderCopy(app.renderer, texture, src, &dest);*/
/*}*/

/*void fill_rect(int x, int y, int w, int h, uint32_t color) {*/
    /*SDL_SetRenderDrawColor(app.renderer,*/
            /*(color >> 24) & 0xFF,*/
            /*(color >> 16) & 0xFF,*/
            /*(color >>  8) & 0xFF,*/
            /*(color >>  0) & 0xFF);*/
    /*SDL_Rect rect = {x,y,w,h};*/
    /*SDL_RenderFillRect(app.renderer, &rect);*/
/*}*/

/*void blit_rect_scaled(SDL_Texture *texture, SDL_Rect *src, int x, int y, int w, int h) {*/
	/*SDL_Rect dest = { .x = x, .y = y, .w = w, .h = h };*/
	/*SDL_RenderCopy(app.renderer, texture, src, &dest);*/
/*}*/



