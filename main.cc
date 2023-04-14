#include <libaudcore/i18n.h>
#include <libaudcore/playlist.h>
#include <libaudcore/plugin.h>

#include <QUrl>
#include <QDateTime>
#include <QFileInfo>

#define EXPORT __attribute__((visibility("default")))
#define APPLICATION_ID "484736379171897345"

class SortPlugin : public GeneralPlugin {

public:
    static const char about[];

    static constexpr PluginInfo info = {
        N_("Sort"),
        "audacious-plugin-sort",
        about
    };

    constexpr SortPlugin() : GeneralPlugin (info, false) {}

    bool init();
    void cleanup();
};

EXPORT SortPlugin aud_plugin_instance;

const char SortPlugin::about[] = N_("Simple Sort Plugin");

time_t get_modified_time(const char* filepath)
{
    QUrl url(filepath);
    QString path = url.toLocalFile();
    QFileInfo file_info(path);
    return file_info.lastModified().toSecsSinceEpoch();
}

static int compare_by_modified_date(const char * a, const char * b)
{
    if(get_modified_time(a) < get_modified_time(b))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

bool SortPlugin::init() {

    Playlist::active_playlist().sort_by_filename(compare_by_modified_date);
    Playlist::active_playlist().activate();
    return true;
}

void SortPlugin::cleanup() {
}

