from apps.dHealth import dHealthClient

# Taken from the Makefile, to update every time the Makefile version is bumped
MAJOR = 1
MINOR = 0
PATCH = 0


# In this test we check the behavior of the device when asked to provide the app version
def test_version(backend):
    # Use the app interface instead of raw interface
    client = dHealthClient(backend)
    # Send the GET_VERSION instruction
    version = client.send_get_version()
    assert version == (MAJOR, MINOR, PATCH)
