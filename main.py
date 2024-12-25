# Load .xpm and adjust colors slightly
input_file = "texture/wall1.xpm"
output_file = "texture/wall2.xpm"

def modify_color(color):
    """Adjust RGB values slightly."""
    r, g, b = int(color[:2], 16), int(color[2:4], 16), int(color[4:6], 16)
    r = min(255, r + 10)  # Increase red slightly
    g = min(255, g + 5)   # Increase green slightly
    b = max(0, b - 10)    # Decrease blue slightly
    return f"{r:02X}{g:02X}{b:02X}"

with open(input_file, "r") as f:
    lines = f.readlines()

with open(output_file, "w") as f:
    for line in lines:
        if '"' in line and '#' in line:
            # Extract color definition
            parts = line.split()
            color_key, color_value = parts[0], parts[-1]
            if color_value.startswith('#'):
                new_color = modify_color(color_value[1:])
                line = line.replace(color_value, f"#{new_color}")
        f.write(line)
