#include <libaudcore/i18n.h>
#include <libaudcore/playlist.h>
#include <libaudcore/plugin.h>
#include <libaudcore/preferences.h>
#include <libaudcore/runtime.h>

#include <QUrl>
#include <QDateTime>
#include <QFileInfo>

#define EXPORT __attribute__((visibility("default")))
#define APPLICATION_ID "484736379171897345"

static const char * const defaults[] = {
    "sort-order", "1",
    nullptr
};
    
static const ComboItem sort_order[] = {
    ComboItem(N_("Oldest First"), 1), 
    ComboItem(N_("Latest First"), -1)
};

void on_change();

static const PreferencesWidget pref_widgets[] = {
    WidgetLabel (N_("<b>Sort</b>")),
    WidgetCombo (N_("Sort Order:"),
    WidgetInt ("sort", "sort-order", on_change),
    {{sort_order}})
};

static const PluginPreferences prefs = {{pref_widgets}};

class SortPlugin : public GeneralPlugin {
    public:
    static const char about[];
    
    static constexpr PluginInfo info = {
        N_("Sort"),
        "audacious-plugin-sort",
        about,
        &prefs
    };
    
    constexpr SortPlugin() : GeneralPlugin (info, false) {}
    
    bool init();
    void cleanup();
};

EXPORT SortPlugin aud_plugin_instance;

const char SortPlugin::about[] = N_("Simple Plugin to Sort by Modification Time");

time_t get_modified_time(const char* filepath)
{
    QUrl url(filepath);
    QString path = url.toLocalFile();
    QFileInfo file_info(path);
    return file_info.lastModified().toSecsSinceEpoch();
}

static int compare_by_modified_date(const char * a, const char * b)
{
    int sort_order = aud_get_int("sort", "sort-order");
    
    if(get_modified_time(a) < get_modified_time(b)) {
        return -1 * sort_order;
    } else {
        return 1 * sort_order;
    }
}

bool SortPlugin::init() {
    aud_config_set_defaults("sort", defaults);
    
    Playlist::active_playlist().sort_by_filename(compare_by_modified_date);
    Playlist::active_playlist().activate();
    return true;
}

void SortPlugin::cleanup() {
}

void on_change() {
    Playlist::active_playlist().sort_by_filename(compare_by_modified_date);
}
